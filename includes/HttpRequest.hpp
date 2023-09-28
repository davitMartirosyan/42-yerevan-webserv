/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:21:43 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/28 20:54:45 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Lib.hpp"
#include "Urlx.hpp"

class HttpRequest
{
    public:
        HttpRequest( std::string const &request);
        ~HttpRequest();
        std::string const &getMethod( void ) const;
        std::string const &getUrl( void ) const;
        std::string const &getHttpVersion( void ) const;
    private:
        void parseHttpRequest(std::string &req);
        void getRequestLine(std::string &req);
        void tokenPairs(std::string &req);
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
        std::string requestMethod;
        std::string requestUrl;
        std::string requestHttpVersion;
};