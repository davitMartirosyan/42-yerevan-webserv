/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:14:58 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/16 00:17:31 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libs.hpp"
#include "ServerManager.hpp"

std::string file(std::string const &filename);

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    try
    {   

        ServerManager mgn("conf/webserv.conf");
        ///////////////////////////////////IN PARSING//////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
            HTTPServer srv;
            srv.setIp("0.0.0.0");
            srv.setPort("5555");
            srv.setRoot("www/server1/");
            srv.setSize("200mb");
            srv.setAutoindex("on");
            srv.pushIndex("index.html");
            srv.pushMethods("GET");
            srv.pushMethods("POST");
            srv.push("aws.amazon.webserv.com");
            
            Location rootLocation; // "/";
            rootLocation.setRoot("/");
            rootLocation.pushIndex("pics.html");
            rootLocation.pushMethods("GET");
            rootLocation.setAutoindex("off"); 
        ///////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
        srv.up(mgn);
            mgn.push_back(srv);
        mgn.set();


        
        fd_set s_rd = mgn.r_set();
        fd_set s_wr = mgn.w_set();
        fd_set s_ex = mgn.e_set();
        while (1)
        {
            sock_t found = 0;
            s_rd = mgn.r_set();
            s_wr = mgn.w_set();
            s_ex = mgn.e_set();
            int i_o = select(mgn.getmax() + 1, &s_rd, &s_wr, NULL, NULL);
            if (i_o > 0)
            {

                for(int i = 0; i <= FD_SETSIZE; i++)
                {
                    if (FD_ISSET(i, &s_rd))
                    {
                        if ((found = mgn.findServerBySocket(i)) != -1)
                        {
                            std::cout << "_______________" << std::endl;
                            std::cout << mgn.getmax() << ":::" << i << std::endl;
                            std::cout << "qtel em servery" << std::endl;
                            std::cout << "_______________" << std::endl;
                            HTTPServer* that = mgn.getServerBySocket(i);
                            sock_t cl = that->accept();
                            Client client(cl);
                            that->push(cl, client);
                            mgn.set_r(cl);
                        }
                        else
                        {                           
                            HTTPServer* server = mgn.getServerByClientSocket(i);
                            Client* client = server->getClient(i);
                            client->appendRequest();
                            
                            // mgn.set_w(client->getFd());
                            
                            std::string response = "HTTP/1.1 200 OK\r\n";
                            response += "\r\n";
                            // response += "<html><head><link rel='shortcut icon' href='data:image/x-icon;,' type='image/x-icon'></head><body><form action='post.php' method='POST' enctype='multipart/form-data'><input type='file' name='pic'><input type='submit' name='send'></form></body></html>";
                            response += file("www/server1/index.html");
                            int wr = send(client->getFd(), response.c_str(), response.size(), 0);
                            close(client->getFd());
                            mgn.rm_r(client->getFd());
                            server->removeClient(client->getFd());
                            response.clear();
                        }
                    } else if (FD_ISSET(i, &s_wr)) {
                        // if ((found = mgn.findClientBySocket(i)) != -1)
                        // {
                            
                        // }
                    }
                }
            }
        }
    }
    catch(std::exception const &e)
    {
        std::cout << e.what() << std::endl;
    }
   
}

std::string file(std::string const &filename)
{
    std::fstream f;
    std::string tmp;
    std::string content;
    f.open(filename.c_str());
    if (f.is_open())
    {
        while (std::getline(f, tmp, '\n'))
        {
            content += tmp;
            tmp.clear();
        }
    }
    return (content);
}




// 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
// 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
// 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


// struct sockaddr
//   {
//     __SOCKADDR_COMMON (sa_);	/* Common data: address family and length.  */
//     char sa_data[14];		/* Address data.  */
//   };

// struct sockaddr_in
//   {
//     __SOCKADDR_COMMON (sin_);
//     in_port_t sin_port;			/* Port number.  */
//     struct in_addr sin_addr;		/* Internet address.  */
//     /* Pad to size of `struct sockaddr'.  */
//     unsigned char sin_zero[sizeof (struct sockaddr) - __SOCKADDR_COMMON_SIZE - sizeof (in_port_t) - sizeof (struct in_addr)];
//   };



// struct addrinfo
// {
//   int ai_flags;			/* Input flags.  */
//   int ai_family;		/* Protocol family for socket.  */
//   int ai_socktype;		/* Socket type.  */
//   int ai_protocol;		/* Protocol for socket.  */
//   socklen_t ai_addrlen;		/* Length of socket address.  */
//   struct sockaddr *ai_addr;	/* Socket address for socket.  */
//   char *ai_canonname;		/* Canonical name for service location.  */
//   struct addrinfo *ai_next;	/* Pointer to next in list.  */
// };
