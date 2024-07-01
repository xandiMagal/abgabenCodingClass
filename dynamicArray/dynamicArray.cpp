/********************************************************************************************************************************************************************
* Name: 	    [Magerl]
* Projekt: 	    [dynamicArray.cpp]
* Erstelldatum: [27.06.2024]
* Beschreibung: [implementiert eine dynamische Array-Klasse DynamicItemArray, die Item-Objekte speichert und verwaltet. Die Item-Klasse repräsentiert ein Objekt 
				 mit einem einzelnen std::uint32_t-Wert. Das Programm demonstriert die Nutzung dieser Klassen, indem es eine Funktion function bereitstellt, 
				 die eine bestimmte Anzahl von Item-Objekten erzeugt, in ein DynamicItemArray einfügt und deren Werte ausgibt.
				 
				 Item-Klasse: Einfache Klasse zur Darstellung eines Objekts mit einem std::uint32_t-Wert.
				 DynamicItemArray-Klasse: Dynamisches Array zur Speicherung von Item-Objekten, das automatisch seine Kapazität anpasst, wenn mehr Platz benötigt wird.
				 Speicherverwaltung: Alle dynamisch erzeugten Item-Objekte werden korrekt verwaltet und freigegeben, um Speicherlecks zu vermeiden
				 function(): Fügt Item-Objekte in das Array ein und gibt deren Werte in der Konsole aus.]
**********************************************************************************************************************************************************************/


#include <cstdint>    // Für std::uint32_t
#include <iostream>
#include <stdexcept>  // Für std::out_of_range

// git test


class Item final
{
	std::uint32_t m_value;
public:
	explicit Item(std::uint32_t value)
		: m_value(value)
	{

	}
	~Item() = default;

	std::uint32_t GetValue() const
	{
		return m_value;
	}
};

class DynamicItemArray
{
private:
	Item **m_items;       // Zeiger auf dynamisches Array von Item-Zeigern
	std::uint32_t m_size; // Aktuelle Anzahl von Items
	std::uint32_t m_capacity; // Maximale Kapazität des Arrays

	void Resize()
	{
		// verdoppelt Kapazität
		std::uint32_t newCapacity = m_capacity * 2;
		Item **newItems = new Item * [newCapacity];

		// Kopiere vorhandene Items in das neue Array
		for (std::uint32_t i = 0; i < m_size; ++i)
		{
			newItems[i] = m_items[i];
		}

		// Altes Array freigeben
		delete[] m_items;

		// Zeiger auf neues Array aktualisieren
		m_items = newItems;
		m_capacity = newCapacity;
	}

public:
	DynamicItemArray()
		: m_items(nullptr), m_size(0), m_capacity(1)
	{
		m_items = new Item * [m_capacity];
	}

	~DynamicItemArray()
	{
		// Alle dynamisch erzeugten Items löschen
		for (std::uint32_t i = 0; i < m_size; ++i)
		{
			delete m_items[i];
		}
		delete[] m_items; // Freigabe des Arrays
	}

	void Add(const Item &item)
	{
		if (m_size == m_capacity)
		{
			Resize();
		}
		m_items[m_size] = new Item(item);
		++m_size;
	}

	const Item &GetItemAtPosition(std::uint32_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return *m_items[index];
	}
};

void function(std::uint32_t count)
{
	DynamicItemArray dynamicArray;
	for (std::uint32_t i = 0; i < count; i++)
	{
		dynamicArray.Add(Item(20 % (i + 1) + i));
	}

	for (std::uint32_t i = 0; i < count; i++)
	{
		const Item &item = dynamicArray.GetItemAtPosition(i);
		std::cout << "Value of the item at position " << i + 1 <<
			" is " << item.GetValue() << std::endl;
	}
}

int main()
{
	function(10);
	return 0;
}