
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
--    local camForward = STGame:Get():getCamera():getForward()
--    local oldX, oldZ = position:getX(), position:getZ()
--    local fX, fZ = camForward:getX(), camForward:getZ()
--    local delta = STGame:Get():getDelta()
--    local speedFactor = self:getAttributef("speedFactor")
--
--    if input:isKeyDown(KEY.KEY_L) then
--        self:transform():setTranslateX(oldX + (speedFactor * delta))
--    elseif input:isKeyDown(KEY.KEY_J) then
--        self:transform():setTranslateX(oldX - (speedFactor * delta))
--    elseif input:isKeyDown(KEY.KEY_I) then
--        self:transform():setTranslateZ(oldZ + (speedFactor * delta))
--    elseif input:isKeyDown(KEY.KEY_K) then
--        self:transform():setTranslateZ(oldZ - (speedFactor * delta))
--    end
    self:transform():setTranslateX(2.0)
    self:transform():setRotateY(counter);
    counter = counter + 0.25 * STGame:Get():getDelta()

end

function onPress(self, other)
    print("This is passing a function as a register. This is being called from a script")
    local lastPosition = self:transform():getTranslate():getY()
    lastPosition = lastPosition+  (0.25 * self:getAttributef("speedFactor"))
    self:transform():setTranslateY(lastPosition)
end