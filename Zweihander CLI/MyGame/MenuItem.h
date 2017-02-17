class MenuItem
{
	char* m_name;
	void (*m_function)();
	MenuItem(const MenuItem&){}
	MenuItem& operator=(const MenuItem&){}
public:
	MenuItem()
	{
		m_name = 0;
		m_function = 0;
	}

	~MenuItem()
	{
		delete[] m_name;
	}

	MenuItem(const char* _name, void (*_function)())
	{
		set(_name, _function);
	}

	void set(const char* _name, void (*_function)())
	{
		m_name = new char[strlen(_name) + 1];
		strcpy_s(m_name, strlen(_name) + 1, _name);
		m_function = _function;
	}

	const char * getName() const { return m_name; }

	void execute() { m_function(); }
};