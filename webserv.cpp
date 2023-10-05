/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:33:26 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/06 01:08:22 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"
#include "HttpMetaProvider.hpp"
#include "HTTPServer.hpp"
HttpMetaProvider Meta;

int main(int ac, const char**av, const char **env)
{
    try
    {
        // addr, family, type, protocol, port, backlog 
        HTTPServer s("127.0.0.1", AF_INET, SOCK_STREAM, 0, 8080, 10);
    }
    catch (std::exception const &e)
    {
        std::cout << e.what() << std::endl;
    }

}
