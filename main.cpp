/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:19:41 by msaadidi          #+#    #+#             */
/*   Updated: 2024/10/25 16:23:40 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NetworkScanner.hpp"

int main()
{
    NetworkScanner NS("10.12.6.2", "10.12.6.10");
    std::string ip = "10.62.6.3";
    NS.pingHost(ip);
    NS.outputResults();
}