/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 00:05:52 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/05 20:47:42 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerManager.hpp"

ServerManager::ServerManager(std::string const &configfile)
{
    (void)configfile;
    FD_ZERO(&s_rd);
    FD_ZERO(&s_wr);
    FD_ZERO(&s_except);
    max_fd = 0;
}

ServerManager::~ServerManager()
{
    
}

void ServerManager::set_w(sock_t fd)
{
    
}

void ServerManager::set_r(sock_t fd)
{
    
}

int ServerManager::used(HTTPServer *srv) const
{
    if (!this->empty())
    {
        for(size_t i = 0; i < this->size(); i++)
        {
            if (std::strcmp((*this)[i].getPort(), srv->getPort()) == 0)
                return (-1);
        }
    }
    return (0);
}

fd_set ServerManager::r_set( void ) const
{
    return (s_rd);
}

fd_set ServerManager::w_set( void ) const
{
    return (s_wr);
}

fd_set ServerManager::e_set( void ) const
{
    return (s_except);
}

// void ServerManager::push(HTTPServer const &srv)
// {
//     srvs.push_back(srv);
// }