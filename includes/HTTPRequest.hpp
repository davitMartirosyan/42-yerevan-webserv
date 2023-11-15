/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:28 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/16 01:49:45 by dmartiro         ###   ########.fr       */
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
        void parsing(sock_t fd);
        std::string const &requestMethod( void ) const;
        std::string const &requestPath( void ) const;
        std::string const &requestVersion( void ) const;
        std::string ltrim(const std::string &str);
        std::string rtrim(const std::string &str);
        std::string trim(const std::string &str);
    protected:
        size_t reqLineEnd;
        size_t bodyEnd;
		char http[READ_BUFFER];
        std::string httpRequest;
        std::string request;
        std::string method;
        std::string path;
        std::string version;
        std::string headers;
        std::string body;
    protected:
        std::map<std::string, std::string> httpHeaders;
    private:
        unsigned long int bodySize;
    private:
        enum t_method{
            GET,
            POST,
            DELETE
        };
};

#endif