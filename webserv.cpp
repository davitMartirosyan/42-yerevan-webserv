/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:14:58 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/28 21:19:12 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libs.hpp"
#include "ServerManager.hpp"
#define PORT 8080
#include <limits.h>
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
        
        struct addrinfo addr, *res;
        addr.ai_family = PF_UNSPEC;
        addr.ai_socktype = SOCK_STREAM;
        addr.ai_flags = AI_PASSIVE;

        if (getaddrinfo(srv.getIp(), srv.getNPort(), &addr, &res) < 0)
            perror("getaddr");
        struct sockaddr_in* a = (struct sockaddr_in*)res->ai_addr;
        // std::cout << htonl(a->sin_addr.s_addr) << std::endl;
        // int fd;

        // if (!res)
        // {
        //     perror("asjgdagsd");
        //     std::cout << "e.what" << std::endl;
        //     exit(1);
        // }

        // if ((fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
        // {
        //     perror("socket"); 
        // }

        // if (bind(fd, (struct sockaddr *)res->ai_addr, res->ai_addrlen) < 0)
        //     perror("asdasdasd");

        // if (listen(fd, 100))
        //     perror("asjdgagsdgasdasd");

        // [0] -> 128          // 00000000 00000000 00000000 10000000
        // [1] -> 32768        // 00000000 00000000 10000000 00000000
        // [2] -> 8388608      // 00000000 10000000 00000000 00000000
        // [3] -> 2147483648   // 10000000 00000000 00000000 00000000


    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

// 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

