#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <SFML/Graphics.hpp>


class Clickable
{
    
    public:
        enum Status {Idle, Pressed, Released, Moved, Hovered};
        enum Type   {Button, ToggleButton, Slider};
        //Constructor
        Clickable(sf::Vector2f size, sf::Vector2f initPosition, Type type);
        Clickable(Type type);

        virtual ~Clickable() = default;
        Clickable(const Clickable&) = delete;
        Clickable& operator=(const Clickable&) = delete;
        Clickable(Clickable&&) noexcept = delete;
        Clickable& operator=(Clickable&&) noexcept = delete;
        
        bool create(unsigned int width, unsigned int height);
        virtual const sf::Vector2f& draw() = 0;

// Getters

        // Return the enum Status of the Object
        Clickable::Status getStatus()          const;
        // Return the position of the Object
        const sf::Vector2f& getPosition()      const;
        // Return the rotation of the Object
        float getRotation()                    const;
        //Return the color of the Object
        const sf::Color& getColor()            const;
        // Return the size of the Object
        const sf::Vector2f& getSize()          const;
        // Return the origin of the Object
        const sf::Vector2f& getOrigin()        const;
        // Return the scale of the Object
        const sf::Vector2f& getScale()         const;
        // Return the global bounds of the Object
        const sf::FloatRect& getGlobalBounds() const;
        // Return the enum Type of the Object
        Type getType()                         const;
        // Return the Sprite Object
        const sf::Sprite& getSprite()          const;
        const sf::Texture& getTexture()        const;

// Setters
        
        // Set the position of the Object
        void setPosition(const sf::Vector2f& newPosition);
        void setPosition(float x, float y);
        void move(const sf::Vector2f& newPosition);
        void move (float x, float y);

        void setRotation(float newRotation);
/*
        void setFillColor(const sf::Color& color);
        void setOutlineColor(const sf::Color& color);
        void setOutlineThickness(float thickness);
*/
        // Set the size of the Object
        void setSize(const sf::Vector2f& newSize);
        void setSize(float width, float height);

        // Set the origin of the Object
        void setOrigin(const sf::Vector2f& newOrigin);
        void setOrigin(float x, float y);

        // Set the scale of the Object
        void setScale(const sf::Vector2f& newScale);
        void setScale(float x, float y);
        void setScale(float scale);

    private:
        sf::Vector2f      size;
        sf::Vector2f      pos;
        sf::RenderTexture renderTexture;
        sf::Sprite        renderSprite;
        Status            status;
        Type              type;

};

#endif
