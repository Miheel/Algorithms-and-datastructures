#include <iostream>
#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

const std::array<std::array<int, 3>, 3> KERNEL_SOBEL_x = { { {-1, 0, 1},
												 {-2, 0, 2},
												 {-1, 0, 1} } };
const std::array<std::array<int, 3>, 3> KERNEL_SOBEL_y = { { {-1, -2, -1},
												 {0, 0, 0},
												 {1, 2, 1} } };
const std::array<std::array<int, 3>, 3> KERNEL_BLUR = { { {1, 1, 1},
												 {1, 1, 1},
												 {1, 1, 1} } };

void sobel(sf::Texture &texture);
void boxblur(sf::Texture & texture);

int convolution(sf::Image &img, int x, int y, const std::array<std::array<int, 3>, 3> &kernel);

void printMask(const std::array<std::array<int, 3>, 3> &arr);

int main(int argc, char** argv) {

	sf::Texture tex;
	if (!tex.loadFromFile("lotus.png"))return EXIT_FAILURE;

	sf::Sprite sprite(tex);

	sf::RenderWindow win(sf::VideoMode(tex.getSize().x, tex.getSize().y), "sobel");
	win.setFramerateLimit(60);

	sprite.scale(win.getView().getViewport().width, win.getView().getViewport().height);

	sf::Event event;
	while (win.isOpen())
	{
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				win.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					boxblur(tex);
					//sobel(tex);
					//
					tex.copyToImage().saveToFile("edge_lotus.png");
				}
			}
		}

		win.clear();
		win.draw(sprite);
		win.display();
	}

	return 0;
}

void sobel(sf::Texture & texture)
{
	sf::Image newImg = texture.copyToImage(), oldImg = texture.copyToImage();
	for (size_t x = 1; x < newImg.getSize().x - 1; x++)
	{
		for (size_t y = 1; y < newImg.getSize().y - 1; y++)
		{
			auto newPixel_x = convolution(oldImg, x, y, KERNEL_SOBEL_x);
			auto newPixel_y = convolution(oldImg, x, y, KERNEL_SOBEL_y);

			auto pixelval = std::min(255, int(sqrt(newPixel_x*newPixel_x + newPixel_y * newPixel_y)));
			newImg.setPixel(x, y, sf::Color(pixelval, pixelval, pixelval));
		}
	}
	texture.update(newImg);
}

void boxblur(sf::Texture & texture)
{
	sf::Image newImg = texture.copyToImage(), oldImg = texture.copyToImage();
	for (size_t x = 1; x < newImg.getSize().x - 1; x++)
	{
		for (size_t y = 1; y < newImg.getSize().y - 1; y++)
		{
			auto newPixel = convolution(oldImg, x, y, KERNEL_BLUR);

			auto pixelval = newPixel / 9;
			newImg.setPixel(x, y, sf::Color(pixelval, pixelval, pixelval));
		}
	}
	texture.update(newImg);
}

int convolution(sf::Image & img, int x, int y, const std::array<std::array<int, 3>, 3> &kernel)
{
	auto imgStart_x = 0;
	auto imgStart_y = y - (kernel[1].size() / 2);
	sf::Color collor;

	int accumulator = 0;
	for (auto kernelRow : kernel) {
		imgStart_x = x - kernel[0].size() / 2;
		for (auto kernelElem : kernelRow)
		{
			collor = img.getPixel(imgStart_x, imgStart_y);
			auto grayscale = 0.2126*collor.r + 0.7152*collor.g + 0.0722*collor.b;
			accumulator += grayscale * kernelElem;
			imgStart_x++;
		}
		imgStart_y++;
	}
	return accumulator;
}

void printMask(const std::array<std::array<int, 3>, 3> &arr)
{
	for (auto x : arr) {
		for (auto elem : x)
		{
			std::cout << elem << ",";
		}
		std::cout << "\n";
	}
}
