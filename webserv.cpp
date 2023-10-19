/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:14:58 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/19 17:36:06 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libs.hpp"
#include "ServerManager.hpp"
#define PORT 8080

int main(int ac, char **av)
{
    struct addrinfo hints, *res, *p;
    int getaddr = getaddrinfo("127.0.0.1", "http", &hints, &res);
    if (getaddr != 0)
        std::cout << "error" << std::endl;
    void *addr;
    struct sockaddr_in* ipv4 = (struct sockaddr_in*)res->ai_addr;
    addr = &(ipv4->sin_addr);
    int ip = ipv4->sin_addr.s_addr;
    std::cout << ip << std::endl;
    std::cout <<( ip >> 8 )<< std::endl;
    std::cout <<( ip >> 16 )<< std::endl;
    std::cout <<( ip >> 24 )<< std::endl;
}

