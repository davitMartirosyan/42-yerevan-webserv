/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:14:58 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/19 02:08:05 by dmartiro         ###   ########.fr       */
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
        int maxfd = 0;
        fd_set rd;
        fd_set wr;
        FD_ZERO(&rd);
        FD_ZERO(&wr);
        
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
        // mgn.set();

        FD_SET(srv.getfd(), &rd);
        maxfd = srv.getfd();

        fd_set tmp_rd;
        fd_set tmp_wr;
        while (1)
        {
            FD_ZERO(&tmp_rd);
            FD_ZERO(&tmp_wr);
            tmp_rd = rd;
            tmp_wr = wr;
            int io = select(maxfd + 1, &tmp_rd, &tmp_wr, NULL, NULL);
            
            for(size_t i = 0; i < mgn.size(); i++)
            {
                if (FD_ISSET(mgn[i].getfd(), &tmp_rd))
                {
                    sock_t cl = mgn[i].accept();
                    Client client(cl);
                    mgn.clnt.push_back(client);
                    FD_SET(cl, &rd);
                    maxfd = std::max(maxfd, cl);
                }
            }

            for(size_t i = 0; i < mgn.clnt.size(); i++)
            {
                if (FD_ISSET(mgn.clnt[i].getFd(), &rd))
                {
                    Client client = mgn.clnt[i];
                    sock_t clfd = client.getFd();
                    
                    client.appendRequest();
                    FD_SET(clfd, &wr);
                }
                if (FD_ISSET(mgn.clnt[i].getFd(), &wr))
                {
                    sock_t clfd = mgn.clnt[i].getFd();
                    std::string response = "HTTP/1.1 200 OK\r\n";
                    response += "Date: Thu, 19 Nov 2023 12:00:00 GMT\r\n";
                    response += "Server: ExampleServer/1.0\r\n";
                    response += "Content-Type: text/html\r\n";
                    response += "Content-Length: 1024\r\n";
                    response += "\r\n";
                    response += file("www/server1/index.html");
                    
                    ssize_t wr = send(clfd, response.c_str(), response.size(), 0);
                    close(clfd);
                    if (clfd == maxfd)
                        maxfd -= 1;
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
