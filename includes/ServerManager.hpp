/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:52:27 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/03 00:16:50 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_MANAGER
#define SERVER_MANAGER
#include "Libs.hpp"
#include "Location.hpp"
#include "HTTPServer.hpp"

class HTTPServer;
class ServerManager : public std::vector<HTTPServer>
{
    public:
        ServerManager(std::string const &configFile);
        ~ServerManager();
    private:
        std::vector<HTTPServer> srvs;
          
};

#endif
