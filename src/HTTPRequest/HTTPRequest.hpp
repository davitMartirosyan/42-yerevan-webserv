/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:28 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/02 00:41:59 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP
#include "Libs.hpp"

class HTTPRequest
{
	public:
		HTTPRequest( void );
		~HTTPRequest();
    protected:
		const char* http;
        std::string httpRequest;
        std::string requestLine;
        std::string body;
    protected:
        std::map<std::string, std::string> httpHeaders;
    private:
        unsigned long int bodySize;
};

#endif