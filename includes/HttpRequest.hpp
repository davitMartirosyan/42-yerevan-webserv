/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:21:43 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/01 17:39:11 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP
#include "Lib.hpp"

class HttpRequest
{
    public:
        HttpRequest( std::string const &request);
        ~HttpRequest();
        std::string const &method( void ) const;
        std::string const &url( void ) const;
        std::string const &httpVersion( void ) const;
        std::string const &getBody( void ) const;
    private:
        void parseHttpRequest(std::string &req);
        void getRequestLine(std::string &req);
        void getHeader(std::string &req);
        void getBody(std::string &req);
    private:
        std::string rtrim(const std::string &s);
        std::string ltrim(const std::string &s);
        std::string trim(const std::string &s);
    private:
        std::vector<std::string> requestLine;
        std::map<std::string, std::string> header;
    private:
        std::string req;
        std::string body;
};
#endif