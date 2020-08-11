<!--[![Stargazers][stars-shield]][stars-url]-->
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/ugo94490/Plazza/">
    <img src="plazza.jpeg" alt="Logo" width="626" height="626">
  </a>

  <h3 align="center">Plazza</h3>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
* [Usage](#usage)
* [Contributor](#contributor)
* [License](#license)
* [Contact](#contact)



<!-- ABOUT THE PROJECT -->
## About The Project

The purpose of this project is to make  a simulation of a pizzeria, which is composed of the reception that accepts new commands, of several kitchens, themselves
with several cooks, themselves cooking several pizzas.

Each kitchen is a fork create in the reception, each cook in the kitchen is a thread to manage many pizza at the same time.

### Built With

There is no specific lib in this project.

<!-- GETTING STARTED -->
## Getting Started

```
$> make
$> ./plazza [TIME MULTIPLIER] [NB_COOK_PER_KITCHEN] [FRIDGE_REFRESH_TIME]
```


<!-- USAGE EXAMPLES -->
## Usage
```
  After launch, you can command a pizza by the following syntax
  
  > TYPE SIZE NUMBER [;...]

  - TYPE = regina|margarita|americaine|fantasia
  - SIZE = S|M|L|XL|XXL
  - NUMBER = x[1..9][0..9]

  Example : regina XXL x2; fantasia M x3; margarita S x1
```


<!-- CONTRIBUTING -->
## Contributor

* [Ugo Levi--Cescutti](https://github.com/ugo94490)
* [Grégroire Lerimeur](https://github.com/lerimeur)
* [Paul Cochet](https://github.com/Paul-Cochet)


<!-- LICENSE -->
## License



<!-- CONTACT -->
## Contact

Ugo Levi--Cescutti - [Linkedin](https://www.linkedin.com/in/ugo-levi-cescutti/) - ugo.levi-cescutti@epitech.eu

Project Link: [https://github.com/ugo94490/Plazza/](https://github.com/ugo94490/Plazza/)

[stars-shield]: https://img.shields.io/github/stars/ugo94490/Plazza/.svg?style=flat-square
[stars-url]: https://github.com/ugo94490/Plazza/stargazers
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/ugo-levi-cescutti/
