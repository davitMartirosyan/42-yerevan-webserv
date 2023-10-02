/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMetaProvider.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:29:03 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/02 16:32:09 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_META_PROVIDER_HPP
#define HTTP_META_PROVIDER_HPP
#include "Lib.hpp"

class HttpMetaProvider
{
    public:
        HttpMetaProvider( void );
        ~HttpMetaProvider();
        std::string mimeType(std::string const &ext);
        std::string httpMethod(std::string const &method);
    private:
        void Mimes( void );
        void Methods( void );
    private:
        std::map<std::string, std::string> types;
        std::vector<std::string> methods;
};
extern HttpMetaProvider Meta;

#endif