/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:28 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/12 21:40:45 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQ_HPP
#define REQ_HPP
#include "Libs.hpp"

class HTTPRequest
{
	public:
		HTTPRequest( void );
		~HTTPRequest();
    public:
        std::string const &requestMethod( void ) const;
        std::string const &requestPath( void ) const;
        std::string const &requestVersion( void ) const;
    protected:
		char http[READ_BUFFER];
        std::string requestLine;
        std::string method;
        std::string path;
        std::string version;
        std::string httpRequest;
        std::string body;
    protected:
        std::map<std::string, std::string> httpHeaders;
    private:
        unsigned long int bodySize;
};

#endif