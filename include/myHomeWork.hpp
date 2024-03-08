#pragma once

#include"check_gl.hpp"

struct HollowCircle
{
	float x, y;				//圆心坐标
	float inner_raduis;		//内圆半径
	float top_raduis;		//外圆半径
	float start_angle;		//绘制圆的起始角度
	float end_angle;		//绘制圆的终止角度

	void setColr(const float R, const float G, const float B);
	void paint();
};