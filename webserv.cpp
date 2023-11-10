/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:14:58 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/10 20:08:22 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libs.hpp"
#include "ServerManager.hpp"

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
            srv.setPort("80");
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
        // for(size_t i = 0; i < 3; i++)
        // {
        //     HTTPServer s1;
        //     s1.setPort(ports[i]);
        //     s1.up(mgn);
        //         mgn.push_back(s1);
        // }
            
        mgn.set();
        // mgn.printFds();
        // exit(0);

        fd_set s_rd = mgn.r_set();
        fd_set s_wr = mgn.w_set();
        fd_set s_ex = mgn.e_set();
        struct timeval tv;
        tv.tv_sec = 3;
        tv.tv_usec = 0;
        while (mgn.getmax())
        {
            s_rd = mgn.r_set();
            s_wr = mgn.w_set();
            s_ex = mgn.e_set();
            int i_o = select(mgn.getmax() + 1, &s_rd, &s_wr, NULL, NULL);
            
            if (i_o > 0)
            {
                for(int i = 0; i < mgn.getmax(); i++)
                {
                    if (FD_ISSET(i, &s_rd))
                    {
                        if (mgn.find(i) != -1)
                        {
                            std::cout << "qtel em servery utem?" << std::endl;
                            HTTPServer* that = mgn.getServer(i);
                            sock_t cl = that->accept();
                            Client client(cl);
                            that->push(cl, client);
                            mgn.set_r(cl);
                        }
                        else
                        {
                            std::cout << "qtel em klientin inch em anum" << std::endl;
                            Client* client = mgn.get(i);
                            char http[1024];
                            int rd = recv(client->getFd(), http, sizeof(http), 0);
                            http[rd] = '\0';
                            std::cout << http << std::endl;
                        }
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
