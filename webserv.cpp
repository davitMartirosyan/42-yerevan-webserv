/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:14:58 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/26 00:32:50 by dmartiro         ###   ########.fr       */
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
        HTTPServer src;
        src.setPort("8080");
        std::cout << src.getPort() << std::endl;
    }
    catch(std::exception const &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::string ip = "127.0.0.1";
}


// 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

