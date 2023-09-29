/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Urlx.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:32:37 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/29 23:02:24 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Urlx.hpp"

Urlx::Urlx(std::string const &url)
{
    this->url = url;
    this->generateParsedUrl();
}

std::string const &Urlx::getUrl( void ) const
{
    return (this->url);
}

void Urlx::generateParsedUrl( void )
{
    std::string tmpurl = url;
    int pos = tmpurl.find("://", 0, 3);
    std::string hostname;
    std::string port;
    std::string path;
    if (pos <= 6 && pos >= 3)
    {
        parsedUrl.push_back(tmpurl.substr(0, pos));
        pos += 3;
    }
    else
    {
        parsedUrl.push_back("nil");
        pos = 0;
    }
    tmpurl = url.substr(pos);
    hostname = tmpurl.substr(0, tmpurl.find("/"));
    if (hostname.find(":") != std::string::npos)
    {
        parsedUrl.push_back(hostname.substr(0, hostname.find(":")));
        parsedUrl.push_back(hostname.substr(hostname.find(":")+1, hostname.find("/")));
    }
    else
    {
        parsedUrl.push_back(hostname.substr(0, hostname.find(":")));
        parsedUrl.push_back("nil");
    }
    tmpurl = tmpurl.substr(hostname.size());
    if (tmpurl.find("#") != std::string::npos)
        parsedUrl.push_back(tmpurl.substr(0, tmpurl.find("#")));
    else
        parsedUrl.push_back("nil");
}

std::string const &Urlx::protocol( void ) const
{
    return (parsedUrl[0]);
}
std::string const &Urlx::domain( void ) const
{
    return (parsedUrl[1]);
}
std::string const &Urlx::port( void ) const
{
    return (parsedUrl[2]);
}
std::string const &Urlx::path( void ) const
{
    return (parsedUrl[3]);
}

Urlx::~Urlx(){}