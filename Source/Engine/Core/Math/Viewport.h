#pragma once


namespace DawnEngine
{
	struct Viewport
	{
	public:

        union
        {
            struct
            {
                float X;

                float Y;
            };

            Vector2 Location;
        };

        union
        {
            struct
            {
                float Width;

                float Height;
            };

            Vector2 Size;
        };

        float MinDepth;

        float MaxDepth;

    public:

        Viewport()
        {
        }

        Viewport(float x, float y, float width, float height)
            : X(x)
            , Y(y)
            , Width(width)
            , Height(height)
            , MinDepth(0.0f)
            , MaxDepth(1.0f)
        {
        }
	};
}