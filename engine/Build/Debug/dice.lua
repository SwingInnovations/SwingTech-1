function start(self)
    addEvent(self, "onCollision");
end

function update(self)

end

function onCollision(self, other)
    print("Collided with: " .. other:getTag())
end