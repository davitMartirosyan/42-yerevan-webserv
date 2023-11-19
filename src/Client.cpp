/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:55 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/19 02:09:17 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client( void )
{
    this->rd = 0;
}

Client::Client(sock_t clfd, sock_t srfd)
{
    this->fd = clfd;
    this->serverFd = srfd;
    this->rd = 0;
}

Client::Client(sock_t clfd)
{
    this->fd = clfd;
    this->serverFd = -1;
}

sock_t Client::getFd( void ) const
{
    return (this->fd);
}

sock_t Client::getServerFd( void ) const
{
    return (this->serverFd);
}

Client::~Client()
{
}


void Client::appendRequest( void )
{
    // int count = 0;
    // while ((rd = recv(fd, http, sizeof(http), 0)) > 0)
    // {
    //     if (rd > 0)
    //     {
    //         count++;
    //         http[rd] = '\0';
    //         httpRequest.append(http);
    //     }
    //     else
    //         break;
    // }
    // rd = recv(fd, http, sizeof(http), 0);
    // if (rd > 0)
    // {
    //     http[rd] = '\0';
    //     httpRequest.append(http, rd);
    // }
    // HTTPRequest::parsing(fd);
    // HTTPRequest::processing(fd);
    size_t reqLineFound = 0;
    size_t headersFound = 0;
    size_t space = 0;
    char *buf = new char[READ_BUFFER];
    std::memset(buf, 0, READ_BUFFER);
    while ((rd = recv(fd, buf, sizeof(READ_BUFFER), 0)) > 0)
    {
        buf[rd] = '\0';
        httpRequest.append(buf);
        if ((reqLineEnd = httpRequest.find_first_of("\r\n")) != std::string::npos && reqLineFound == 0)
        {
            request = httpRequest.substr(0, reqLineEnd);
            for (size_t i = 0; i < request.size(); i++)
                if (std::isspace(request[i]))
                    space++;
            if (space == 2)
            {
                method = trim(request.substr(0, request.find_first_of(" ")));
                request.erase(0, request.find_first_of(" ") + 1);
                path = trim(request.substr(0, request.find_first_of(" ")));
                request.erase(0, request.find_first_of(" ") + 1);
                version = trim(request.substr(0, request.find("\r\n")));
                // std::cout << "|"<<method<<"|" << std::endl;
                // std::cout << "|"<<path<<"|" << std::endl;
                
                // std::cout << "|"<<version<<"|" << std::endl;
                reqLineFound = 1;
                httpRequest.erase(0, reqLineEnd + 2);
            }
        }
        if ((bodyEnd = httpRequest.find("\r\n\r\n")) != std::string::npos && headersFound == 0)
        {
            std::stringstream iss(httpRequest);
            std::string get_next_line;
            while (std::getline(iss, get_next_line) && get_next_line != "\r\n")
            {
                // std::cout << "|"<<trim(get_next_line)<<"|" << std::endl;
                size_t colon;
                if ((colon = get_next_line.find_first_of(":")) != std::string::npos && std::isspace(get_next_line[colon+1]))
                {
                    std::string key = trim(get_next_line.substr(0, colon));
                    std::string value = trim(get_next_line.substr(colon+2, get_next_line.find("\r\n")));
                    std::cout << key << " - " << value << std::endl;
                }
            }
            httpRequest.erase(0, bodyEnd + 4);
            // charChange(httpRequest, '\r', '*');
            // charChange(httpRequest, '\n', '*');
            headersFound = 1;
        }
    }
    std::cout << httpRequest << std::endl;
}