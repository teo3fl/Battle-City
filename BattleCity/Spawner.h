#pragma once

template <class T>
class Spawner
{
public:
	Spawner(const uint8_t& numberOfObjects) : m_numberOfObjects(numberOfObjects)
	{
	}
	~Spawner()
	{
		while (!m_objects.empty())
		{
			delete m_objects.front();
			m_objects.pop();
		}
	}

	void AddTexture(const sf::Texture& texture, const std::string& textureName)
	{
		m_textures[textureName] = texture;
	}

	bool IsEmpty()
	{
		return m_objects.empty();
	}

	T* SpawnNext()
	{
		T* object = m_objects.front();
		m_objects.pop();

		sf::Vector2f currentSpawningPoint = m_spawnPoints[GetCurrentSpawningPoint()];
		object->SetPosition(currentSpawningPoint.x, currentSpawningPoint.y);
		return object;
	}

protected:
	virtual uint8_t GetCurrentSpawningPoint() = 0;
	virtual void SetSpawnPoints() = 0;

protected:
	std::queue<T*> m_objects;
	uint8_t m_numberOfObjects;
	std::map<std::string, sf::Texture> m_textures;

	std::vector<sf::Vector2f> m_spawnPoints;
};

