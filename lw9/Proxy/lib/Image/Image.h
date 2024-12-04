#pragma once
#include "../CoW/CoW.h"
#include "../Geom/Geom.h"
#include "Tile.h"
#include <iosfwd>
#include <string>
#include <vector>

class Image
{
public:
	/**
     * Конструирует изображение заданного размера. Если размеры не являются положительными,
     * выбрасывает исключение std::out_of_range.
     */
	Image(Size size, uint32_t color = ' ');

	// Возвращает размер изображения в пикселях.
	Size GetSize() const noexcept;

	/**
     * Возвращает «цвет» пикселя в указанных координатах.Если координаты выходят за пределы
     * изображения, возвращает «пробел».
     */
	uint32_t GetPixel(Point p) const noexcept;

	/**
     * Задаёт «цвет» пикселя в указанных координатах. Если координаты выходят за пределы изображения
     * действие игнорируется.
     */
	void SetPixel(Point p, uint32_t color);

private:
	std::vector<std::vector<CoW<Tile>>> m_tiles;
	Size m_size;
};

/**
 * Выводит в поток out изображение в виде символов.
 */
void Print(const Image& img, std::ostream& out);

/**
 * Загружает изображение из pixels. Линии изображения разделяются символами \n.
 * Размеры картинки определяются по количеству переводов строки и самой длинной линии.
 */
Image LoadImage(const std::string& pixels);

void SaveImage(const Image& image, const std::string& fileName);
