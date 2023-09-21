/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Urlx.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:31:54 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/22 01:07:08 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Lib.hpp"

class Urlx
{
    public:
        Urlx(std::string const &url);
        ~Urlx();
    public:
        std::string const &getProto( void ) const;
        std::string const &getHostname( void ) const;
        std::string const &getPort( void ) const;
        std::string const &getPath( void ) const;
        std::string const &getUrl( void ) const;
    private:
        std::vector<std::string> protocols;
        std::string theUrl;
        std::string proto;
        std::string hostname;
        std::string port;
        std::string path;
};