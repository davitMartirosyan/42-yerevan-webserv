/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:26:17 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/28 01:29:45 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP
#include "Libs.hpp"
#include <unordered_map>

class HTTPResponse
{
    public:
        HTTPResponse( void );
        ~HTTPResponse();
    public:
        std::string const &getResponse( void ) const;
        std::string const &getReserve404( void ) const;
        std::string const &getReserve403( void ) const;
        std::string const &getReserve(int statusCode) const;
        std::unordered_map<std::string, std::string> &getResponseHeader();
        void addHeader(const std::pair<std::string, std::string> &);
        void buildHeader();
        void setCgiPipeFd(int fd);
    protected:
        std::string _response;
        std::unordered_map<std::string, std::string> _responseHeader;
        int _cgiPipeFd;
    private:
        std::string reserve;
};

#endif