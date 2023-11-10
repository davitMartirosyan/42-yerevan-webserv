/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 00:05:52 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/10 01:00:48 by dmartiro         ###   ########.fr       */
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

void ServerManager::printFds( void )
{
    for(int i = 0; i < FD_SETSIZE; i++)
        if (FD_ISSET(i, &s_rd))
            std::cout << i << std::endl;
}

HTTPServer *ServerManager::getServer(sock_t fd)
{
    for(size_t i = 0; i < this->size(); i++)
    {
        if (fd == (*this)[i].getfd())
            return (&(*this)[i]);
    }
    return (NULL);
}

Client *ServerManager::get(sock_t fd)
{
    for(size_t i = 0; i < this->size(); i++)
    {
        Client* clnt = (*this)[i].client(fd);
        if (clnt)
            return (clnt);
    }
    return (NULL);
}

void ServerManager::setmax(sock_t lastfd)
{
    if (lastfd == -1)
        return ;
    max_fd = lastfd;
}

sock_t ServerManager::getmax( void ) const
{
    return (max_fd);
}

void ServerManager::set( void )
{
    for(size_t i = 0; i < this->size(); i++)
        set_r((*this)[i].getfd());
}

void ServerManager::set_w(sock_t fd)
{
    if (fd == -1)
        return ;
    FD_SET(fd, &s_wr);
    setmax(fd);
}

void ServerManager::set_r(sock_t fd)
{
    if (fd == -1)
        return ;
    FD_SET((int)fd, &s_rd);
    setmax(fd);
}

void ServerManager::set_e(sock_t fd)
{
    if (fd == -1)
        return ;
    FD_SET(fd, &s_except);
    setmax(fd);
}

int ServerManager::used(HTTPServer *srv) const
{
    if (!this->empty())
    {
        for(size_t i = 0; i < this->size(); i++)
            if (std::strcmp((*this)[i].getPort(), srv->getPort()) == 0)
                return (-1);
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

sock_t ServerManager::find(sock_t issetfd) const
{
    if (issetfd == -1)
        return (-1);
    for(size_t i = 0; i < this->size(); i++)
    {
        if (issetfd == (*this)[i].getfd())
            return ((*this)[i].getfd());
    }
    return (-1);
}

int ServerManager::isServer(sock_t fd)
{
    return (0);
}

int ServerManager::isClient(sock_t fd)
{
    return (0);
}

// void ServerManager::push(HTTPServer const &srv)
// {
//     srvs.push_back(srv);
// }