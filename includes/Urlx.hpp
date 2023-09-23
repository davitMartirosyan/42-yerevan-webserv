/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Urlx.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:31:54 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/24 02:19:56 by dmartiro         ###   ########.fr       */
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
        std::string const &getUrl( void ) const;
        std::string const &protocol( void ) const;
        std::string const &domain( void ) const;
        std::string const &port( void ) const;
        std::string const &path( void ) const;
    private:
        void generateParsedUrl( void );
        std::vector<std::string> parsedUrl;
        std::string url;
};