--Initialize stuff here
function init(self)
    AddEvent(self, "onCollision")
    AddEvent(self, "onRayHit")
    self:setAttributei("hasChanged", 0)
    local randR = math.random()
    local randG = math.random()
    local randB = math.random()
    GetRendererComponent(self):getMaterial():setDiffuseColor(Vector4.new(randR, randG, randB, 1.0));
end

--Called Every Frame
function update(self)
    local input = STGame:Get():getInput()
    local tY = self:transform():getTranslate():getY()
    if(input:isKeyPressed(KEY.KEY_I)) then
        Remove(self)
    end

    if input:isKeyPressed(KEY.KEY_O) then
        self:setAttributei("hasChanged", 0)
    end

    if(tY <= -5.0)then
        Remove(self)
    end
end

-- On Collision Callback
function onCollision(self, other)
    if other:getName() == "Plane" and self:getAttributei("hasChanged") == 0 then
        self:setAttributei("hasChanged", 1)
        local randR = math.random()
        local randG = math.random()
        local randB = math.random()
        local newColor = Vector4.new(randR, randG, randB, 1.0)
        GetRendererComponent(self):getMaterial():setDiffuseColor(newColor)
        end
end

-- On Rayhit Flag
function onRayHit(self, other)
    print("On Ray hit")
end