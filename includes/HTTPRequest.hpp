/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:28 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/14 01:23:14 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQ_HPP
#define REQ_HPP
#include "Libs.hpp"

enum parse_typeface
{
    PARSE_SUCCESS = 0,
    HTTP_REQUEST_LINE_ERROR = -1, 
    HTTP_HEADER_ERROR = -2
};
class HTTPRequest
{
	public:
		HTTPRequest( void );
		~HTTPRequest();
    public:
        parse_typeface parse(char *httpBuffer);
        const char *find(std::string const &key);
    public:
        std::string const &requestMethod( void ) const;
        std::string const &requestPath( void ) const;
        std::string const &requestVersion( void ) const;
        std::string ltrim(const std::string &str);
        std::string rtrim(const std::string &str);
        std::string trim(const std::string &str);
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