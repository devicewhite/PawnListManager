#if defined _list_included
	#endinput
#endif
#define _list_included

#pragma library list

/* Fake Natives
native List_PushFront(list, value);
native List_PushBack(list, value);
native List_Insert(list, index, value);

native List_PopFront(list);
native List_PopBack(list);
native List_Remove(list, index);

native List_PopFrontEx(list, &value);
native List_PopBackEx(list, &value);
native List_RemoveEx(list, index, &value);

native List_Sort(list);
native List_Clear(list);
native List_Reverse(list);

native List_FindValue(list, value);
native List_SetValue(list, index, value);
native List_GetValue(list, index);

native List_FindValueEx(list, value, &index);
native List_GetValueEx(list, index, &value);

native List_Count(list);
native List_IsEmpty(list);
native List_IsFull(list);

native List_Contains(list, value);
*/

#define ListManager:%1<%2> _@list_%1[%2], _@top_%1 = -1, _@max_%1 = %2
/*
 * Example:
 * 	new ListManager:Test<10>;
 *
 * Same code:
 * 	new _@list_Test[10], _@top_Test = -1, _@max_Test = 10;
 */

#if defined __FOREACH_STYLE
	#define List_ForEach(%1\32;%2\32;:%0\32;%3) \
		for(%1 __idx, %2 = _@list_%3[0]; __idx <= _@top_%3 && %2 <= cellmax; %2=_@list_%3[++__idx])

	/*
	 * Example:
	 * 	List_ForEach(new i : Test) {
	 * 		printf("Value %d at position %d\n", i, __idx);
	 * 	}
	 *
	 * Same code:
	 * 	for(new __idx, i = _@list_Test[0]; __idx <= _@top_Test && i <= cellmax; i = _@list_Test[++__idx]) {
	 * 		printf("Value %d at position %d\n", i, __idx);
	 * 	}
	 */
#else
	#define List_ForEach(%1;%2;%3) \
		for(new %1 = _@list_%2[0], __idx = %3; __idx <= _@top_%2 && %1 <= cellmax; %1 = _@list_%2[++__idx])

	/*
	 * Example:
	 * 	List_ForEach(i;Test;3) {
	 * 		printf("Value %d at position %d\n", i, __idx);
	 * 	}
	 *
	 * Same code:
	 * 	for(new i = _@list_Test[0], __idx = 3; __idx <= _@top_Test && i <= cellmax; i = _@list_Test[++__idx]) {
	 * 		printf("Value %d at position %d\n", i, __idx);
	 * 	}
	 */
#endif

#define List_PushFront(%1,%2) \
	_@_list_push_front(_@list_%1, _@top_%1, _@max_%1, %2)

stock _@_list_push_front(list[], &top, max, value)
{
	if(top >= (max - 1)) return 0;

	for(new i = ++top; i > 0; i--)
		list[i] = list[i - 1];

	list[0] = value;
	return 1;
}

#define List_PushBack(%1,%2) \
	_@_list_push_back(_@list_%1, _@top_%1, _@max_%1, %2)

stock _@_list_push_back(list[], &top, max, value)
{
	if(top >= (max - 1)) return 0;
	list[++top] = value;
	return 1;
}

#define List_Insert(%1,%2,%3) \
	_@_list_insert(_@list_%1, _@top_%1, _@max_%1, %2, %3)

stock _@_list_insert(list[], &top, max, index, value)
{
	if(top >= (max - 1)) return 0;

	for(new i = ++top; i >= index; i--)
		list[i] = list[i - 1];

	list[index] = value;
	return 1;
}

#define List_PopBack(%1,%2) \
	_@_list_pop_back(_@list_%1, _@top_%1)

stock _@_list_pop_back(list[], &top)
{
	if(top == -1) return 0;
	new value = list[top];
	list[top--] = 0;
	return value;
}

#define List_PopBackEx(%1,%2) \
	_@_list_pop_back_ex(_@list_%1, _@top_%1, %2)

stock _@_list_pop_back_ex(list[], &top, &value)
{
	if(top == -1) return 0;
	value = _@_list_pop_back(list, top);
	return 1;
}

#define List_PopFront(%1) \
	_@_list_pop_front(_@list_%1, _@top_%1)
	
stock _@_list_pop_front(list[], &top)
{
	if(top == -1) return 0;
	new value = list[0];
	
	for(new i; i < top; i++)
	{
		list[i] = list[i + 1];
		list[i + 1] = 0;
	}

	top--;
	return value;
}

#define List_PopFrontEx(%1,%2) \
	_@_list_pop_front_ex(_@list_%1, _@top_%1, %2)
	
stock _@_list_pop_front_ex(list[], &top, &value)
{
	if(top == -1) return 0;
	value = _list_pop_front(list, top);
	return 1;
}

#define List_Remove(%1,%2) \
	_@_list_remove(_@list_%1, _@top_%1, %2)

stock _@_list_remove(list[], &top, index)
{
	if(top == -1 || index > top || index < 0) return 0;
	new value = list[index];
	
	for(new i = index; i < top; i++)
	{
		list[i] = list[i + 1];
		list[i + 1] = 0;
	}

	top--;
	return value;
}

#define List_RemoveEx(%1,%2,%3) \
	_@_list_remove_ex(_@list_%1, _@top_%1, %2, %3)

stock _@_list_remove_ex(list[], &top, index, &value = 0)
{
	if(top == -1 || index > top || index < 0) return 0;
	value = _list_remove(list, top, index);
	return 1;
}

#define List_Reverse(%1) \
	_@_list_reverse(_@list_%1, _@top_%1)

stock _@_list_reverse(list[], top)
{
	if(top <= 0) return 0;

	for(new idx, size = top, tmp; idx < size; idx++, size--)
	{
		tmp = list[idx];
		list[idx] = list[size];
		list[size] = tmp;
	}
	return 1;
}

#define List_Sort(%1) \
	_@_list_sort(_@list_%1, _@top_%1)

stock _@_list_sort(list[], top)
{
	if(top <= 0) return 0;

	for(new idx, minus, tmp; idx < top; idx++)
	{
		minus = idx;
		for(new idx2 = idx + 1; idx2 <= top; idx2++)
		{
			if(list[idx2] < list[minus])
				minus = idx2;
		}

		if(minus != idx)
		{
			tmp = list[idx];
			list[idx] = list[minus];
			list[minus] = tmp;
		}
	}
	return 1;
}

#define List_FindValue(%1,%2) \
	_@_list_find(_@list_%1, _@top_%1, %2)

stock _@_list_find(const list[], top, value)
{
	if(top == -1) return 0;
	new index = -1;

	for(new i; i <= top; i++)
	{
		if(list[i] == value)
		{
			index = i;
			break;
		}
	}
	return index;
}

#define List_FindValueEx(%1,%2,%3) \
	_@_list_find_ex(_@list_%1, _@top_%1, %2, %3)

stock _@_list_find_ex(const list[], top, value, &index)
{
	if(top == -1) return 0;
	index = _list_find(list, top, value);
	return 1;
}
	
#define List_Clear(%1) \
	_@_list_clear(_@list_%1, _@top_%1, _@max_%1)

stock _@_list_clear(list[], &top, max)
{
	if(top == -1) return 0;

	for(new i; i < max; i++)
		list[i] = EOS;

	top = -1;
	return 1;
}

#define List_SetValue(%1,%2,%3) \
	_@_list_set_value(_@list_%1, _@top_%1, _@max_%1, %2, %3)

stock _@_list_set_value(list[], &top, max, index, value)
{
	if(top >= (max - 1) || index < 0 || index > top) return 0;
	list[index] = value;
	return 1;
}

#define List_GetValue(%1,%2) \
	_@_list_get_value(_@list_%1, _@top_%1, %2)

stock _@_list_get_value(const list[], top, index)
{
	if(top == -1 || !(0 <= index <= top)) return 0;
	return list[index];
}

#define List_GetValueEx(%1,%2,%3) \
	_@_list_get_value_ex(_@list_%1, _@top_%1, %2, %3)

stock _@_list_get_value_ex(const list[], top, index, &value)
{
	if(top == -1 || !(0 <= index <= top)) return 0;
	value = list[index];
	return 1;
}

#define List_Count(%1) (_@top_%1 + 1)

#define List_IsEmpty(%1) (_@top_%1 == -1)

#define List_IsFull(%1) (_@top_%1 == _@max_%1 - 1)

#define List_Contains(%1,%2) (List_Find(%1,%2) >= 0)


// PRE-DEFINED LISTS FOR THE SYSTEM

new
	ListManager:Actors<MAX_ACTORS>,
	ListManager:NPCs<MAX_PLAYERS>,
	ListManager:Players<MAX_PLAYERS>,
	ListManager:Vehicles<MAX_VEHICLES>;

public OnPlayerConnect(playerid)
{
	if(IsPlayerNPC(playerid))
	{
		List_PushBack(NPCs, playerid);
		List_Sort(NPCs);
	}
	else
	{
		List_PushBack(Players, playerid);
		List_Sort(Players);
	}

	#if defined List_PlayerConnect
		List_PlayerConnect(playerid);
	#endif
	return 1;
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect List_PlayerConnect
#if defined List_PlayerConnect
	forward List_PlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	new index;
	if(IsPlayerNPC(playerid))
	{
		index = List_FindValue(NPCs, playerid);
		List_Remove(NPCs, index);
	}
	else
	{
		index = List_FindValue(Players, playerid);
		List_Remove(Players, index);
	}

	#if defined List_PlayerDisconnect
		List_PlayerDisconnect(playerid, reason);
	#endif
	return 1;
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect List_PlayerDisconnect
#if defined List_PlayerDisconnect
	forward List_PlayerDisconnect(playerid, reason);
#endif

stock List_CreateActor(skin, Float:x, Float:y, Float:z, Float:angle)
{
	new actorId = CreateActor(skin, x, y, z, angle);
	List_PushBack(Actors, actorId);
	List_Sort(Actors);
	return actorId;
}
#if defined _ALS_CreateActor
	#undef CreateActor
#else
	#define _ALS_CreateActor
#endif
#define CreateActor List_CreateActor

stock List_DestroyActor(actorid)
{
	new actorId = List_FindValue(Actors, actorid);
	List_Remove(Actors, actorId);
	return DestroyActor(actorid);
}
#if defined _ALS_DestroyActor
	#undef DestroyActor
#else
	#define _ALS_DestroyActor
#endif
#define DestroyActor List_DestroyActor

stock List_AddStaticVehicle(modelid, Float:spawnX, Float:spawnY, Float:spawnZ, Float:angle, colour1, colour2)
{
	new vehId = AddStaticVehicle(modelid, spawnX, spawnY, spawnZ, angle, colour1, colour2);
	List_PushBack(Vehicles, vehId);
	List_Sort(Vehicles);
	return vehId;
}
#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif
#define AddStaticVehicle List_AddStaticVehicle

stock List_AddStaticVehicleEx(modelid, Float:spawnX, Float:spawnY, Float:spawnZ, Float:angle, colour1, colour2, respawnDelay, bool:addSiren = false)
{
	new vehId = AddStaticVehicleEx(modelid, spawnX, spawnY, spawnZ, angle, colour1, colour2, respawnDelay, addSiren);
	List_PushBack(Vehicles, vehId);
	List_Sort(Vehicles);
	return vehId;
}
#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif
#define AddStaticVehicleEx List_AddStaticVehicleEx

stock List_CreateVehicle(modelid, Float:spawnX, Float:spawnY, Float:spawnZ, Float:angle, colour1, colour2, respawnDelay, bool:addSiren = false)
{
	new vehId = CreateVehicle(modelid, spawnX, spawnY, spawnZ, angle, colour1, colour2, respawnDelay, addSiren);
	List_PushBack(Vehicles, vehId);
	List_Sort(Vehicles);
	return vehId;
}
#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif
#define CreateVehicle List_CreateVehicle

stock List_DestroyVehicle(vehicleid)
{
	new id vehId List_FindValue(Vehicles, vehicleid);
	List_Remove(Vehicles, vehId);
	return DestroyVehicle(vehicleid);
}
#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif
#define DestroyVehicle List_DestroyVehicle
