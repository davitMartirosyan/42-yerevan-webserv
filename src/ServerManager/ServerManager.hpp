/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:52:27 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/14 00:26:53 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_HPP
#define TCP_HPP
#include "Libs.hpp"
#include "HTTPServer.hpp"

class ServerManager
{
    public:
        ServerManager(const char *config); // Իմիտացիա ենք անում յանի ստեղ կոնֆիգ ֆայլը parse ա լինում :D
        ~ServerManager();
    public:
        void createServerInstances( void );
    private:
        int srvsCount;
        std::map<int, HTTPServer> srvs;
};

#endif
