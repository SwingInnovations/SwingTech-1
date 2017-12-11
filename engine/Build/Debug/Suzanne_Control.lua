
-- Initialize Variables Here
function start(self)
    print("Initializing Script")
    addEvent(self, "onPress")
end

counter = 0;

--This is called every frame.
function update(self)
    local input = STGame:Get():getInput()
    local position = self:transform():getTranslate()
    local camForward = STGame:Get():getCamera():getForward()
    local oldX, oldZ = position:getX(), position:getZ()
    local delta = STGame:Get():getDelta()
    local speedFactor = self:getAttributef("speedFactor")

    if input:isKeyDown(KEY.KEY_L) then
        self:transform():setTranslateX(oldX + (speedFactor * delta))
    elseif input:isKeyDown(KEY.KEY_J) then
        self:transform():setTranslateX(oldX - (speedFactor * delta))
    elseif input:isKeyDown(KEY.KEY_I) then
        self:transform():setTranslateZ(oldZ + (speedFactor * delta))
    elseif input:isKeyDown(KEY.KEY_K) then
        self:transform():setTranslateZ(oldZ - (speedFactor * delta))
    end
    self:transform():setRotateY(counter);
    counter = counter + 0.025 * STGame:Get():getDelta()
end