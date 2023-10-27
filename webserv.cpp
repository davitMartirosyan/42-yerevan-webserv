/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:14:58 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/27 11:06:37 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libs.hpp"
// #include "ServerManager.hpp"
#include "HTTPServer.hpp"

#define PORT 8080

// const char* inet_addr_pton(uint32_t ipv);
int main(int ac, char **av)
{
    try
    {
        HTTPServer srv;
        srv.setIp("127.0.255.1");
        srv.setPort("5000");
        srv.setRoot("www/server1/");
        srv.setSize("200mb");
        srv.setAutoindex("on");
        srv.pushIndex("index.html");
        srv.pushMethods("GET");
        srv.pushMethods("POST");
        
        
        Location rootLocation; // "/";
        rootLocation.pushIndex("pics.html");
        rootLocation.pushMethods("GET");
        rootLocation.setAutoindex("off");

        
        srv.pushLocation("/pictures", rootLocation);   
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    
}


// 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

