/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:26:17 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/26 02:12:48 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP
#include "Libs.hpp"

class HTTPResponse
{
    public:
        HTTPResponse( void );
        ~HTTPResponse();
    public:
        std::string file(std::string const &filename);
        std::string const &getResponse( void ) const;
    protected:
        std::string response;
};

#endif