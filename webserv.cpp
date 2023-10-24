/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:14:58 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/24 10:21:44 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libs.hpp"
// #include "ServerManager.hpp"
#include "HTTPServer.hpp"

#define PORT 8080

const char* inet_addr_pton(uint32_t ipv);

int main(int ac, char **av)
{
    HTTPServer srv("127.0.0.1", "8080");
    std::cout << srv.getAutoindex() << std::endl;
}

