for (const auto& teacher : teachers) 
        {
            if (teacher.m_type == "2" && teacher.m_class == this->m_class) 
            {
                cout << "    ID: " << teacher.m_id << " | Name: " << teacher.m_name << endl;
                studentIdsInClass.push_back(teacher.m_id);
            }
        }