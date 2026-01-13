#pragma once

#include<SFML/Graphics.hpp>
#include<vector>

class ParticleSystem {

    struct Particle {
        sf::Vector2f velocity;
        int lifetime = 0;
    };

    std::vector<Particle>   m_particles;
    sf::VertexArray         m_vertices;
    sf::Vector2u            m_windowSize;
    float                   m_size = 8;
    sf::Vector2f            m_emitter;

    void resetParticles(size_t count = 1024, float size = 8){
        m_particles = std::vector<Particle>(count);
        m_vertices = sf::VertexArray(sf::PrimitiveType::Points, count);
        m_size = size;
        
        for(size_t p=0; p<m_particles.size(); p++) {
            resetParticle(p,true);
        }
    }

    void resetParticle(std::size_t index, bool first = false) {

        
        m_vertices[index].position = m_emitter;
        // m_vertices[index*3+1].position = sf::Vector2(mx+m_size,my);
        // m_vertices[index*3+2].position = sf::Vector2(mx,my+m_size);
        
        //give particle a color
        sf::Color color(255,rand()%255,0,rand()%255);
        // sf::Color color(255,255,255,rand()%255);
        
        if(first) {
            color.a = 0;
        }

        m_vertices[index].color = color;
        // m_vertices[index*3+1].color = color;
        // m_vertices[index*3+2].color = color;


        //give the particle a random velocity
        float rx = ((float)rand() / RAND_MAX)*10-5; //reandom value btw -5 to 5
        float ry = ((float)rand() / RAND_MAX)*10-5;

        m_particles[index].velocity = sf::Vector2f(rx,ry);

        //give the particle a life span
        m_particles[index].lifetime = 30+ rand()%60;
    }

    public:

    ParticleSystem() {

    };

    void init(sf::Vector2u windowSize){
        m_windowSize = windowSize;
        float mx = m_windowSize.x/2;
        float my = m_windowSize.y/2;
        setEmitter({mx,my});
        resetParticles();
    }

    void update() {
        for(size_t i=0; i<m_particles.size(); i++) {

            if(m_particles[i].lifetime == 0) {
                resetParticle(i);
            }

            m_vertices[i].position += m_particles[i].velocity;
            // m_vertices[i*3+1].position += m_particles[i].velocity; 
            // m_vertices[i*3+2].position += m_particles[i].velocity;

            m_particles[i].lifetime--;
        }
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(m_vertices);
    }

    void setEmitter(const sf::Vector2f& pos) {
        m_emitter = pos;
    }

};