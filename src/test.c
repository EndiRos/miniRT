obj->props = props;
obj->next = NULL; // Asegúrate de terminar la lista

if (!(*scene)->objects)
{ 
    (*scene)->objects = obj;
    return (0); 
}

last_obj = (*scene)->objects;
while (last_obj->next)
    last_obj = last_obj->next;

last_obj->next = obj;  // Aquí enlazas el nuevo objeto al final

return (0);