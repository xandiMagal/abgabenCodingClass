/*****************************************************************************************************************************
* Name: 	    [Magerl]
* Projekt: 	    [dynamicArray_extension]
* Erstelldatum: [28.06.2024]
* Beschreibung: [Kurze Beschreibung der Funktionalität]
******************************************************************************************************************************/


#include <sstream>
#include <iostream>
#include <memory>
#include <stdexcept>


class IItem
{
public:
	virtual ~IItem() = default;
	virtual std::uint32_t GetValue() const = 0;
	virtual std::string GetText() const = 0;
};

// Klasse ItemA implementiert IItem
class ItemA final : public IItem
{
	std::uint32_t m_value;
public:
	explicit ItemA(std::uint32_t value)
		: m_value(value)
	{
	}

	std::uint32_t GetValue() const override
	{
		return m_value;
	}

	std::string GetText() const override
	{
		std::ostringstream stringStream;
		stringStream << "ItemA with value " << m_value;
		return stringStream.str();
	}
};

// Klasse ItemB implementiert IItem
class ItemB final : public IItem
{
	std::uint32_t m_value;
public:
	explicit ItemB(std::uint32_t value)
		: m_value(value)
	{
	}

	std::uint32_t GetValue() const override
	{
		return m_value;
	}

	std::string GetText() const override
	{
		std::ostringstream stringStream;
		stringStream << "ItemB with value " << m_value;
		return stringStream.str();
	}
};

// Klasse DynamicItemArray zur Verwaltung von IItem-Objekten
class DynamicItemArray
{
private:
	std::unique_ptr<std::unique_ptr<IItem>[]> m_items; // unique pointer auf ein Array von unique pointern auf IItem-Objekte
	std::uint32_t m_size; // Anzahl d. gespeicherten Elemente
	std::uint32_t m_capacity; // maximale Kapazität d. Arrays

	// vergrößert Array, wenn Kapazität erreicht
	void Resize()
	{
		std::uint32_t newCapacity = m_capacity * 2; // verdoppelt Kapazität
		auto newItems = std::make_unique<std::unique_ptr<IItem>[]>(newCapacity); // neues Array mit neuer Kapazität
		
		// Kopieren der alten Elemente in das neue Array
		for (std::uint32_t i = 0; i < m_size; ++i)
		{
			newItems[i] = std::move(m_items[i]);
		}
		m_items = std::move(newItems); // Austausch des alten Arrays mit dem neuen Array
		m_capacity = newCapacity; // Aktualisieren der Kapazität
	}

public:
	// Konstruktor: initialisiert das Array mit einer Anfangskapazität von 1 und einer aktuellen Größe von 0
	DynamicItemArray()
		: m_size(0), m_capacity(1)
	{
		m_items = std::make_unique<std::unique_ptr<IItem>[]>(m_capacity); // erstellt und initialisiert ein neues Array von std::unique_ptr<IItem>
	}

	~DynamicItemArray() = default;

	// Fügt ein neues Element zum Array hinzu
	void Add(std::unique_ptr<IItem> item)
	{
		if (m_size == m_capacity)
		{
			Resize();
		}
		m_items[m_size] = std::move(item);
		++m_size;
	}

	// Gibt einen Zeiger auf das Element an der angegebenen Position zurück
	IItem *GetItemAtPosition(std::uint32_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_items[index].get();
	}
};

// Funktion zum Auffüllen und Drucken der Elemente in DynamicItemArray
void function(std::uint32_t count)
{
	DynamicItemArray dynamicArray;
	for (std::uint32_t i = 0; i < count; i++)
	{
		if (i % 2)
		{
			dynamicArray.Add(std::make_unique<ItemA>(20 % (i + 1) + i));
		}
		else
		{
			dynamicArray.Add(std::make_unique<ItemB>(20 % (i + 1) + i));
		}
	}

	for (std::uint32_t i = 0; i < count; i++)
	{
		const IItem &item = *dynamicArray.GetItemAtPosition(i);
		std::cout << "Value of the item at position " << i + 1 << " is " << item.GetText() << std::endl;
	}
}

int main() {
	function(10);
	return 0;
}

