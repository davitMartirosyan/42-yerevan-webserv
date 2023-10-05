/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:24:38 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/05 22:44:33 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP
#include "Lib.hpp"

class HTTPRequest
{
    public:
        HTTPRequest( void );
        ~HTTPRequest();
    public:
        std::string const &getMethod( void );
        std::string const &getPath( void );
        std::string const &getVersion( void );
    private:
        std::map<std::string, std::string> header;
    private:
        unsigned long int content_length;
        char *request_buffer;
    private:
        std::string method;
        std::string path;
        std::string version;
        std::string body;
};

#endif