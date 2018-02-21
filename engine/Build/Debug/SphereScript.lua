--Initialize stuff here
function init(self)
    print("Initializing Script")
    AddEvent(self, "onCollision")
    AddEvent(self, "onRayHit")
    self:setAttributei("hasChanged", 0)
end

function update(self)

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
        Remove(self)
        end
end

-- On Rayhit Flag
function onRayHit(self, other)
    print("On Ray hit")
end