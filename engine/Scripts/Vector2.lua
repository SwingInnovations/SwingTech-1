local Vector2 = { 
    _x = 0,
    _y = 0,
    addX = function(self, x)
            self._x = self._x + x
            end
    ,        
    addY = function(self, y)
            self._y = self._y + y
            end
}

return Vector2
