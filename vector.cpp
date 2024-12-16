template<typename V>
class Vector
{
    public:
        Vector()
        {
            arr = nullptr; size = 0;

        }

        Vector(int new_size)
        {
            arr = new V[new_size];
            full_size = new_size;
            size = 0;
        }

        void add(int pos, V value)
        {
            ensure_capacity();
            for (int i = size - 1; i > pos-2; i--)
                arr[i+1] = arr[i];
            arr[pos - 1] = value;
            size++;
        }

        void push_back(V new_value)
        {
            this->add(size, new_value);
        }

        void remove(int pos)
        {
            V* new_arr = new V[full_size];
            int flag = 0;

            for (int i = -1; i < size; i++)
            {
                if(i == pos)
                {
                    flag = 1;
                }
                else
                {
                    if(flag == 0)
                    {
                        new_arr[i] = arr[i];
                    }
                    else
                    {
                        new_arr[i-1] = arr[i];
                    }
                }
            }
            delete[] arr;
            arr = new_arr;
            size--;
        }

        void ensure_capacity()
        {
            if (size >= full_size - 1)
            {
                V* new_arr = new V[full_size * 2];
                for (int i = 0; i < size; i++)
                {
                    new_arr[i] = arr[i];
                }
                delete[] arr;
                arr = new_arr;
            }
        }

        int get_size()
        {
            return size;
        }

        V get_value(int pos)
        {
            return arr[pos - 1];
        }

        V operator[](int index)
        {
            return arr[index];
        }

        int find(V _val)
        {
            for (int i = 0; i < size; i++)
            {
                if (arr[i] == _val)
                    return i;
            }
            return -1;
        }

    private:
        V* arr;
        int size;
        int full_size;
};
