/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:14:58 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/23 23:58:45 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libs.hpp"
#include "ServerManager.hpp"
#define PORT 8080

const char* inet_addr_pton(uint32_t ipv);

int main(int ac, char **av)
{
    HTTPServer srv("127.0.0.1", "8080");
    srv.pushIndex("index.html");
    srv.pushIndex("home.html");
    srv.pushMethods("GET");
    srv.pushMethods("POST");
    srv.pushMethods("DELETE");
    srv.setRoot("www/nginx/");
    srv.setAutoindex("off");
    std::cout << srv.getAutoindex() << std::endl;
}

