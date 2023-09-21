/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Urlx.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:32:37 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/22 01:15:35 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"


Urlx::Urlx(std::string const &url)
{
    protocols.push_back("http://");
    protocols.push_back("https://");
    protocols.push_back("ftp://");
    theUrl = url;
    size_t pos;
    for(size_t i = 0; i < protocols.size(); i++)
    {
        pos = theUrl.find(protocols[i]);
        if (pos != std::string::npos)
        {
            proto = theUrl.substr(pos, protocols[i].size() - 3);
            break;
        }
    }
    if (pos == std::string::npos)
        proto = "http";
}

std::string const &Urlx::getUrl( void ) const
{
    return (this->theUrl);
}

std::string const &Urlx::getProto( void ) const
{
    return (this->proto);
}

std::string const &Urlx::getHostname( void ) const
{
    return (this->hostname);
}

std::string const &Urlx::getPort( void ) const
{
    return (this->port);
}

std::string const &Urlx::getPath( void ) const
{
    return (this->path);
}


Urlx::~Urlx(){}