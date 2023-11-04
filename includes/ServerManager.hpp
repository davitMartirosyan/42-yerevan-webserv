/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:52:27 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/04 16:55:48 by dmartiro         ###   ########.fr       */
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
    public:
        int used(HTTPServer *srv) const;
    private:
        std::vector<HTTPServer> srvs;
    public:
        void set_w(sock_t fd);
        void set_r(sock_t fd);
        fd_set r_set( void ) const;
        fd_set w_set( void ) const;
        fd_set e_set( void ) const;
    private:
        int max_fd;
        fd_set s_rd;
        fd_set s_wr;
        fd_set s_except;
};

#endif
