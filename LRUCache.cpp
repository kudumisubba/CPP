// Solution to hackerrank problem - Abstract Classes - Polymorphism
// From the discussion board help - TheCodeHere

LRUCache::LRUCache(int c)
	{
		cp = c; // Capacity
	}

	// Implement set function
	void LRUCache::set(int k, int v) {
		Node* N;             // Pointer to Node, so that we can add to the cache

		if (mp.empty())     // mp is a member in Cache, its a map containing Node entries
		{					// If no nodes are present
			N = new Node(k, v);
			tail = head = N;    // Set both tail and head to N, first node
			mp[k] = N;			// Whatever key (k) is passed add N to it as value			
			return;
		}

		// If mp is not empty search through its keys to add new value
		auto it = mp.find(k);

		if (it != mp.end())  // If the iterator contains a value, meaning find was successful
		{
			it->second->value = v;  // update existing value

			if (head == it->second)  // only one node, no links to update
				return;

			// Doubly linked list, so update both previous and next nodes

			it->second->prev->next = it->second->next;
			/*  This confusing line above means, join the previous node, to the node next to CURRENT node
			*   Which means, the current node is orphaned
			*/

			if (tail == it->second) // If its the last node
			{
				tail = tail->prev; // Point back one node
			}
			else
			{
				// Point next node previous to CURRENT previous, effectively removing CURRENT
				it->second->next->prev = it->second->prev;
			}

			// In this doubly linked list, nodes are always added to the front
			it->second->next = head; // CURRENT node becomes head, current head becomes 2nd node
			it->second->prev = NULL;  // Head nodes previous is NULL

			head->prev = it->second; // ?? - shouldnt this be NULL
			head = it->second;	// head points to new node
		}
		else // Nothing found
		{
			// New Node , head previous is always the NULL in a doubly linked list
			Node* N = new Node(head->prev, head, k, v);

			head->prev = N; // Point current head previous to this new node, as current head becomes second node
			head = N;       // This new node becomes head
			mp[k] = N;

			if (mp.size() > cp) // If capacity has been reached
			{
				tail = tail->prev; // Make the last but one the tail
				mp.erase(tail->next->key); // The last member of the cache is lost
				delete tail->next;
				tail->next = NULL; // tail next is always NULL in a doubly linked list
			}

		}
	}

	int LRUCache::get(int k)
	{
		auto it = mp.find(k);

		if (it != mp.end())
			return it->second->value;

		return -1;
	}
