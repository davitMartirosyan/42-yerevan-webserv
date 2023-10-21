/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:14:58 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/21 11:36:38 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libs.hpp"
#include "ServerManager.hpp"
#define PORT 8080

const char* inet_addr_pton(uint32_t ipv);

int main(int ac, char **av)
{
    std::map<int, HTTPServer> srvs;
    srvs.insert(std::make_pair(3, HTTPServer(3)));
    
    srvs[0].getServerSocket();
}

