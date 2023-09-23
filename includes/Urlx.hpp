/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Urlx.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:31:54 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/23 16:00:46 by dmartiro         ###   ########.fr       */
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
        std::string const &getProto( void ) const;
        void generateParsedUrl( void );
    private:
        std::vector<std::string> parsedUrl;
        std::string url;
};