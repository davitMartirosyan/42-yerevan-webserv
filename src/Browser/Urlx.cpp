/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Urlx.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:32:37 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/23 16:25:03 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"

Urlx::Urlx(std::string const &url)
{
    this->url = url;
}

std::string const &Urlx::getUrl( void ) const
{
    return (this->url);
}

void Urlx::generateParsedUrl( void )
{
    size_t pos = url.find("://", 0, 3);
    if (pos <= 6 && pos >= 3)
    {
        parsedUrl.push_back(url.substr(0, pos));
    }
    else
    {
        parsedUrl.push_back("nil");
        pos = 0;
    }
    size_t begin = pos;
    while (pos < url.size() && url[pos] != '/') pos++;
    std::string hostname_port = url.substr(begin, pos);
    std::cout << hostname_port << std::endl;
}

std::string const &Urlx::getProto( void ) const
{
    return (this->parsedUrl[0]);
}


Urlx::~Urlx(){}