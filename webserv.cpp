/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:14:58 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/29 23:40:18 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libs.hpp"
#include "ServerManager.hpp"


int main(int ac, char **av)
{
    try
    {   
        HTTPServer srv;
        srv.setIp("127.0.0.1");
        srv.setPort("8080");
        srv.setRoot("www/server1/");
        srv.setSize("200mb");
        srv.setAutoindex("on");
        srv.pushIndex("index.html");
        srv.pushMethods("GET");
        srv.pushMethods("POST");
        Location rootLocation; // "/";
        rootLocation.setRoot("/");
        rootLocation.pushIndex("pics.html");
        rootLocation.pushMethods("GET");
        rootLocation.setAutoindex("off");
        srv.pushLocation("/pictures", rootLocation);
        
        if (srv.up(srv.getIp(), srv.getPort(), 5) != 0)
            std::cout << gai_strerror(srv.err()) << std::endl;

        // Tcp::up(HTTPServer const &srvRef);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

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
