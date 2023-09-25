/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:21:43 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/25 19:32:00 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Lib.hpp"

class HttpRequest
{
    public:
        HttpRequest( std::string const &request);
        ~HttpRequest();
    private:
        std::vector<std::string>
}