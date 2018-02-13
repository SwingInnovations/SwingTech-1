
-- Initialize Variables Here
function start(self)
    print("Initializing Script")
    addEvent(self, "onCollision");
end

counter = 0;

--This is called every frame.
function update(self)
    local input = STGame:Get():getInput()
    local position = self:transform():getTranslate()
    local rotation = self:transform():getRotate()
    local oldX, oldZ = position:getX(), position:getZ()
    local rotY = rotation:getY()
    local forward = self:transform():getRight()
    local delta = STGame:Get():getDelta()
    local speedFactor = self:getAttributef("speedFactor")

    if input:isKeyDown(KEY.KEY_L) then
        rotY = rotY + 1;
    elseif input:isKeyDown(KEY.KEY_J) then
        rotY = rotY - 1;
    end
        self:transform():setRotateY(rotY);

    if input:isKeyDown(KEY.KEY_I) then
        self:transform():setTranslateX(oldX + forward:getX() * (speedFactor * delta))
        self:transform():setTranslateZ(oldZ + forward:getZ() * (speedFactor * delta))
    elseif input:isKeyDown(KEY.KEY_K) then
        self:transform():setTranslateX(oldX - forward:getX() * (speedFactor * delta))
        self:transform():setTranslateZ(oldZ - forward:getZ() * (speedFactor * delta))
    end
end

function onCollision(self, other)
    print("A Collision Occured!");
end